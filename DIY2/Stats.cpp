#include "Stats.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

namespace seneca {
    void Stats::load_from_file(Stats &stats) const {

        std::ifstream file(stats.m_filename);
        if (!file.is_open()) return;
        size_t count = 0;
        double temp;
        while (file >> temp) {
            count++;
            if (file.peek() == ',') file.ignore();
        }
        if (count == 0) return;
        stats.m_array_size = count;
        stats.m_stats = new double[m_array_size];
        file.clear();
        file.seekg(0, std::ios::beg);
        for (size_t i = 0; i < count; ++i) {
            file >> stats.m_stats[i];
            if (file.peek() == ',') file.ignore();
        }
    }
    Stats::Stats(unsigned columnWidth, unsigned noOfColumns, unsigned precision) :
    m_column_width(columnWidth), m_columns(noOfColumns),m_precision(precision) {}

    Stats::Stats(const char *filename, unsigned columnWidth, unsigned noOfColumns, unsigned precision) {

        m_column_width = columnWidth;
        m_columns = noOfColumns;
        m_precision = precision;
        if (!filename) return;
        if (std::ifstream file(filename); file.is_open()) {
            m_filename = filename;
            load_from_file(*this);
        }
    }
    Stats::Stats(const Stats &stats) {

        m_column_width = stats.m_column_width;
        m_columns = stats.m_columns;
        m_precision = stats.m_precision;
        m_array_size = stats.m_array_size;
        m_filename = stats.m_filename.empty()? "" : "C_" + stats.m_filename;
        if (stats.m_stats and m_array_size > 0) {
            m_stats = new double[m_array_size];
            for (unsigned i = 0u; i < m_array_size; ++i) m_stats[i] = stats.m_stats[i];
        }
        if (!stats.m_filename.empty()) {
            std::ifstream infile(stats.m_filename);
            std::ofstream outfile(m_filename);
            outfile << infile.rdbuf();
        }
    }
    Stats &Stats::operator=(const Stats &stats) {

        if (this != &stats) {
            delete[] m_stats;
            m_stats = nullptr;
            m_column_width = stats.m_column_width;
            m_columns = stats.m_columns;
            m_precision = stats.m_precision;
            m_array_size = stats.m_array_size;
            m_filename = stats.m_filename.empty()? "" : "C_" + stats.m_filename;
            if (stats.m_stats and m_array_size > 0) {
                m_stats = new double[m_array_size];
                for (unsigned i = 0u; i < m_array_size; ++i) m_stats[i] = stats.m_stats[i];
            }
            if (!stats.m_filename.empty()) {
                std::ifstream infile(stats.m_filename);
                std::ofstream outfile(m_filename);
                outfile << infile.rdbuf();
           }
        }
        return *this;
    }
    double &Stats::operator[](unsigned idx) {

        static double dummy = 0.0;
        if (m_array_size == 0) return dummy;
        return m_stats[idx % m_array_size];
    }
    double Stats::operator[](unsigned idx) const {

        if (m_array_size == 0) return 0.0;
        return m_stats[idx % m_array_size];
    }
    Stats::operator bool() const {

        return m_stats;
    }
    void Stats::sort(bool ascending) {

        if (ascending) std::sort(m_stats, m_stats + m_array_size);
        else std::sort(m_stats, m_stats + m_array_size, std::greater<double>());
    }
    unsigned Stats::size() const {

        return m_array_size;
    }
    const char *Stats::name() const {

        return m_filename.c_str();
    }
    unsigned Stats::occurrence(double min, double max, std::ostream &ostr) {

        int count = 0u;
        for (size_t i = 0; i < m_array_size; ++i) {
            if (m_stats[i] >= min and m_stats[i] <= max) {
                count++;
                ostr << std::setw(static_cast<int>(m_column_width)) << std::setprecision(static_cast<int>(m_precision))
                << m_stats[i] << '\n';
            }
        }
        return count;
    }
    std::ostream& operator<<(std::ostream &ostr, const Stats& stats) {

        if (!stats) return ostr;
        unsigned columns = 0;
        for (int i = 0u; i < stats.m_array_size; ++i) {
            ostr << std::setw(static_cast<int>(stats.m_column_width))
            << std::setprecision(static_cast<int>(stats.m_precision)) << stats.m_stats[i];
            columns++;
            if (columns == stats.m_columns) {
                ostr << '\n';
                columns = 0u;
            }
        }
        if (columns != 0) ostr << '\n';
        return ostr;
    }
    std::istream& operator>>(std::istream &istr, Stats &stats) {

        istr >> stats.m_filename;
        stats.load_from_file(stats);
        return istr;
    }
}
