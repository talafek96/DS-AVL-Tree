#include "Boom.h"

namespace DS
{

    //if false is returned then there is no course with the given id
    //If returned true then the remove succeeded
    bool Boom::removeCourseAux(int course_id)
    {
        if(course_id<=0)
        {
            throw InvalidInput();
        }
        if(!course_tree.find(course_id))
        {
            return false;
        }
        //if we reached here then course with the given id exists.
        Array<std::shared_ptr<graph_node<LectureContainer, int>>>& lecture_arr = course_tree.at(course_id);
        int num_of_classes = lecture_arr.size();
        for (int i=0; i<num_of_classes; i++)
        {
            if(lecture_arr[i]!= nullptr)
            {
                lecture_tree.erase(lecture_arr[i]->key);
                lecture_arr[i]= nullptr;
            }
        }
        course_tree.erase(course_id);
        lecture_counter-=num_of_classes;
        return true;
    }

    //If false is returned then there is no course with the given id,
    //If true is returned then the watch succeeded
    bool Boom::WatchClass(int course_id, int class_id, int time)
    {
        if(time<=0 || class_id<0 || course_id<=0)
        {
            throw InvalidInput();
        }
        if(!course_tree.find(course_id))
        {
            return false;
        }

        Array<std::shared_ptr<graph_node<LectureContainer, int>>>& lecture_arr = course_tree.at(course_id);

        if(class_id+1>lecture_arr.size())
        {
            throw InvalidInput();
        }

        int new_views = 0;
        if(lecture_arr[class_id] !=  nullptr)//Class has views>0
        {
            new_views = lecture_arr[class_id]->key.views;
            lecture_tree.erase(lecture_arr[class_id]->key);
        }
        new_views += time;
        LectureContainer new_lecture = {new_views, course_id, class_id};
        lecture_tree.insert(new_lecture, new_views);
        lecture_arr[class_id] = lecture_tree.getNode(new_lecture);
        return true;
    }

    bool Boom::TimeViewed(int course_id, int class_id, int *time_viewed)
    {
        if(class_id < 0 || course_id <= 0)
        {
            throw InvalidInput();
        }
        if(!course_tree.find(course_id))
        {
            return false;
        }

        Array<std::shared_ptr<graph_node<LectureContainer, int>>>& lecture_arr = course_tree.at(course_id);

        if(class_id + 1 > lecture_arr.size())
        {
            throw InvalidInput();
        }

        *time_viewed = lecture_arr[class_id]->val;
        return true;
    }


}


