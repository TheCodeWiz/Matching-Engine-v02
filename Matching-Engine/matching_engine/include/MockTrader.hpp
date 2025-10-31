#ifndef MOCK_TRADER_HPP
#define MOCK_TRADER_HPP

#include <random>
#include <thread>
#include <chrono>
#include "OrderBook.hpp"

class MockTrader {
public:
    MockTrader(std::shared_ptr<OrderBook> orderBook, const std::string& traderId, int instrumentId)
        : orderBook_(orderBook)
        , traderId_(traderId)
        , instrumentId_(instrumentId)
        , running_(false)
        , engine_(std::random_device{}())
        , priceDistribution_(90.0, 110.0)
        , quantityDistribution_(1, 100)
        , sleepDistribution_(100, 2000)
        , sideDistribution_(0, 1)
    {}

    void start() {
        running_ = true;
        thread_ = std::thread(&MockTrader::run, this);
    }

    void stop() {
        running_ = false;
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    void run() {
        while (running_) {
            // Random sleep between orders
            std::this_thread::sleep_for(
                std::chrono::milliseconds(sleepDistribution_(engine_)));

            // Generate random order parameters
            auto side = sideDistribution_(engine_) == 0 ? OrderSide::BUY : OrderSide::SELL;
            auto price = priceDistribution_(engine_);
            auto quantity = quantityDistribution_(engine_);

            // Create and submit order
            auto order = std::make_shared<Order>(
                OrderType::LIMIT,
                side,
                price,
                quantity,
                TimeInForce::GTC,
                traderId_,
                instrumentId_
            );

            orderBook_->addOrder(order);
        }
    }

    std::shared_ptr<OrderBook> orderBook_;
    std::string traderId_;
    std::atomic<bool> running_;
    std::thread thread_;
    
    std::mt19937 engine_;
    std::uniform_real_distribution<double> priceDistribution_;
    std::uniform_int_distribution<size_t> quantityDistribution_;
    std::uniform_int_distribution<size_t> sleepDistribution_;
    std::uniform_int_distribution<int> sideDistribution_;
    int instrumentId_;
};

#endif // MOCK_TRADER_HPP