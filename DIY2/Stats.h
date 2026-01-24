#ifndef STATS_H
#define STATS_H
#include <string>
#include <iostream>

namespace seneca {

    class Stats {
        //data members
        unsigned m_column_width{};
        unsigned m_columns{};
        unsigned m_precision{};
        double* m_stats{};
        std::string m_filename{};
        size_t m_array_size{};
        //private helper
        void load_from_file(Stats& stats) const;

    public:
        // constructors
        Stats(unsigned columnWidth = 15,
              unsigned noOfColumns = 4,
              unsigned precision = 2);
        Stats(const char* filename,
              unsigned columnWidth = 15,
              unsigned noOfColumns = 4,
              unsigned precision = 2);
        Stats(const Stats& stats);
        //assignment
        Stats& operator=(const Stats& stats);
        //destructor
        ~Stats() = default;
        //element access
        double& operator[](unsigned idx);
        double operator[](unsigned idx)const;
        //state
        operator bool()const;
        unsigned size()const;
        const char* name()const;
        //operations
        void sort(bool ascending);
        unsigned occurrence(double min, double max, std::ostream& ostr = std::cout);
        //i/o operators
        friend std::ostream& operator<<(std::ostream& ostr, const Stats& stats);
        friend std::istream& operator>>(std::istream& istr, Stats& stats);
    };
}
#endif //STATS_H
