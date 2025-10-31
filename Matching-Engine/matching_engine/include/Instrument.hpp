#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>
#include <vector>

struct Instrument {
    std::string name;
    std::string symbol;
    int instrumentId;

    Instrument(const std::string& n, const std::string& s, int id)
        : name(n), symbol(s), instrumentId(id) {}
};

class InstrumentManager {
public:
    static InstrumentManager& getInstance() {
        static InstrumentManager instance;
        return instance;
    }

    const std::vector<Instrument>& getInstruments() const { return instruments_; }

    const Instrument* getInstrumentById(int id) const {
        for (const auto& instrument : instruments_) {
            if (instrument.instrumentId == id) {
                return &instrument;
            }
        }
        return nullptr;
    }

private:
    InstrumentManager() {
        // Initialize with instruments from the image
        instruments_ = {
            Instrument("Reliance Industries", "RELIANCE (NSE)", 1),
            Instrument("Tata Consultancy Services", "TCS (NSE)", 2),
            Instrument("Dixon Technologies", "DIXON (NSE)", 3),
            Instrument("HDFC Bank", "HDFCBANK (NSE)", 4),
            Instrument("Tata Motors", "TATAMOTORS (NSE)", 5),
            Instrument("Tata Power", "TATAPOWER (NSE)", 6),
            Instrument("Adani Enterprises", "ADANIENT (NSE)", 7),
            Instrument("Adani Green Energy", "ADANIGREEN (NSE)", 8),
            Instrument("Adani Power", "ADANIPOWER (NSE)", 9),
            Instrument("Tanla Platforms", "TANLA (NSE)", 10),
            Instrument("Nifty 50 Index", "NIFTY 50", 11),
            Instrument("Bank Nifty Index", "BANKNIFTY", 12),
            Instrument("FinNifty", "FINNIFTY", 13),
            Instrument("Sensex", "SENSEX", 14),
            Instrument("Nifty Next 50 Index", "NIFTY NEXT 50", 15)
        };
    }

    std::vector<Instrument> instruments_;
};

#endif // INSTRUMENT_HPP