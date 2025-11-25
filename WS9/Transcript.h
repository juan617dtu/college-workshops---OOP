#ifndef SENECA_TRANSCRIPT_H
#define SENECA_TRANSCRIPT_H
#include <iostream>
#include "Marks.h"
namespace seneca {
    class Transcript :
       public Marks {
        // character pointer student name
        char* m_student_name{};
        // unsigned integer or size_t student number
        unsigned int m_student_id{};
    public:
        // Constructor
        Transcript(char* name, unsigned int number);
        // Rule of Three
        Transcript(const Transcript& other);
        Transcript& operator=(const Transcript& other);
        // Destructor
        ~Transcript();
        std::ostream& display(std::ostream& ostr = std::cout)const override;
    };
}
#endif // !SENECA_TRANSCRIPT_H

