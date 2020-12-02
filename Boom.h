#ifndef _BOOM_H
#define _BOOM_H
#include "avl_tree/AVL.h"

namespace DS
{
    struct LectureContainer
    {
        int views;
        int course;
        int lecture;

        bool operator<(const LectureContainer& other)
        {
            if(views < other.views)
            {
                return true;
            }
            else if(views > other.views)
            {
                return false;
            }
            // If reached this point, views == other.views
            if(course > other.course)
            {
                return true;
            }
            else if(course < other.course)
            {
                return false;
            }
            // If reached this point, views == other.views && course == other.course
            if(lecture > other.lecture)
            {
                return true;
            }
            return false;
        }

        bool operator==(const LectureContainer& other)
        {
            return (views == other.views) && (course == other.course) && (lecture == other.lecture);
        }

        bool operator!=(const LectureContainer& other)
        {
            return !(*this == other);
        }

        bool operator<=(const LectureContainer& other)
        {
            return (*this < other) || (*this == other);
        }

        bool operator>(const LectureContainer& other)
        {
            return !(*this <= other);
        }

        bool operator>=(const LectureContainer& other)
        {
            return (*this > other) || (*this == other);
        }
    };

    class Boom
    {
    private:
        /* data */
    public:
        Boom(/* args */);
        ~Boom();
    };    
}
#endif