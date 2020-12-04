#include "Boom.h"

namespace DS
{
    bool Boom::addCourse(int course_id, int numOfClasses)
    {
        if (numOfClasses <= 0 || course_id <= 0)
        {
            throw InvalidInput();
        }
        if(course_tree.find(course_id))
        {
            return false;
        }

        // If we got to this point the input is valid and the course is yet to be in the system.
        Array<graph_node<LectureContainer, int>*> lecture_arr(numOfClasses);
        for(int i = 0; i < numOfClasses; i++) // Initialize the array in O(numOfClass) time.
        {
            lecture_arr[i] = nullptr; // nullptr in an array cell means that the lecture has yet to recieve any views.
        }
        lecture_counter += numOfClasses;
        course_tree.insert(course_id, lecture_arr);
        return true;
    }

    // If false is returned then there is no course with the given ID
    // If returned true then the remove succeeded
    bool Boom::removeCourse(int course_id)
    {
        if(course_id<=0)
        {
            throw InvalidInput();
        }
        if(!course_tree.find(course_id))
        {
            return false;
        }
        // If we reached here then course with the given id exists.
        Array<graph_node<LectureContainer, int>*>& lecture_arr = course_tree.at(course_id);
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

    // If false is returned then there is no course with the given id,
    // If true is returned then the watch succeeded
    bool Boom::watchClass(int course_id, int class_id, int time)
    {
        if(time<=0 || class_id<0 || course_id<=0)
        {
            throw InvalidInput();
        }
        if(!course_tree.find(course_id))
        {
            return false;
        }

        Array<graph_node<LectureContainer, int>*>& lecture_arr = course_tree.at(course_id);

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
        lecture_arr[class_id] = lecture_tree.getNode(new_lecture).get();
        return true;
    }

    bool Boom::timeViewed(int course_id, int class_id, int *time_viewed)
    {
        if(class_id < 0 || course_id <= 0)
        {
            throw InvalidInput();
        }
        if(!course_tree.find(course_id))
        {
            return false;
        }

        Array<graph_node<LectureContainer, int>*>& lecture_arr = course_tree.at(course_id);

        if(class_id + 1 > lecture_arr.size())
        {
            throw InvalidInput();
        }

        *time_viewed = lecture_arr[class_id]? lecture_arr[class_id]->val : 0;
        return true;
    }

    bool Boom::getMostViewedClasses(int numOfClasses, int *courses, int *classes)
    {
        if(numOfClasses <= 0)
        {
            throw InvalidInput();
        }
        if(numOfClasses > lecture_counter)
        {
            return false;
        }

        // Create a functor to apply over the lectures that have views:
        class UpdateMostViewedClasses
        {
        public:
            int counter;
            int *courses;
            int *classes;

            explicit UpdateMostViewedClasses(int* courses, int* classes) :
            counter(0), courses(courses), classes(classes) { }
            void operator()(const std::shared_ptr<graph_node<LectureContainer, int>>& lecture)
            {
                courses[counter] = (lecture->key).course;
                classes[counter] = (lecture->key).lecture;
                counter++;
            }
        };
        // Apply the functor to the lecture_tree in a reverse in-order traversal starting from the rightmost node:
        UpdateMostViewedClasses views_functor(courses, classes);
        lecture_tree.reverseInOrder(views_functor, numOfClasses);

        assert(views_functor.counter <= numOfClasses);
        if(views_functor.counter < numOfClasses)
        {
            // In this case we need to go to the course tree and add the lectures that have no views too.
            // Create a functor to apply over the lectures that have no views:
            class UpdateNotViewedClasses
            {
            public:
                int old_counter; // The counter from the previous functor
                int new_counter; // The index shift for the new position in the arrays
                int *courses;
                int *classes;

                explicit UpdateNotViewedClasses(int old_counter, int* courses, int* classes) :
                old_counter(old_counter), new_counter(0), courses(courses), classes(classes) { }
                void operator()(const std::shared_ptr<graph_node<int, Array<graph_node<LectureContainer, int>*>>>& course,
                                int* k)
                {
                    if(*k <= 0) // All the numOfClasses lectures are already inserted into the arrays.
                    {
                        return; // (Shouldn't even get here)
                    }
                    // Check each one of the lectures in the course and add it to the arrays if it has no views:
                    int index = old_counter + new_counter;
                    int size = (course->val).size(); // Number of lectures in the course
                    for(int i = 0; i < size; i++)
                    {
                        if(course->val[i] == nullptr)
                        {
                            // Insert the class into the arrays:
                            courses[index] = course->key;
                            classes[index] = i;
                            index++;
                            new_counter++;
                            (*k)--;
                            if(*k <= 0) // If this was the last class to add, stop inserting to the arrays.
                            {
                                return;
                            }
                        }
                    }
                }
            };
            int remaining_classes = numOfClasses - (views_functor.counter);
            UpdateNotViewedClasses no_views_functor(views_functor.counter, courses, classes);
            course_tree.inOrder(no_views_functor, remaining_classes);
        }
        return true;
    }
}