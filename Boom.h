#ifndef _BOOM_H
#define _BOOM_H
#include "avl_tree/AVL.h"
#include "Array.h"

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
        AVL<int, Array<std::shared_ptr<graph_node<LectureContainer, int>>>> course_tree;
        AVL<LectureContainer, int> lecture_tree;
        int lecture_counter;
    public:
        Boom(/* args */);
        ~Boom();
        class  InvalidInput{};
        bool removeCourseAux(int course_id);
        bool WatchClass(int course_id, int class_id, int time);
        bool TimeViewed(int course_id, int class_id, int *time_viewed);
    };    
}
#endif