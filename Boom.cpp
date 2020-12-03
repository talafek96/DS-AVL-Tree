#include "Boom.h"

namespace DS
{
    bool Boom::addCourse(int course_id, int numOfClasses)
    {
        if (numOfClasses <= 0 || course_id <= 0)
        {
            throw InvalidInput();
        }
        if(!course_tree.find(course_id))
        {
            return false;
        }

        // If we got to this point the input is valid and the course is yet to be in the system
        Array<std::shared_ptr<graph_node<LectureContainer, int>>> lecture_arr(numOfClasses);
        for(int i = 0; i < lecture_arr.size(); i++) // Initialize the array in O(numOfClass) time.
        {
            lecture_arr[i] = nullptr; // nullptr in an array cell means that the lecture has yet to recieve any views.
        }
        lecture_counter += lecture_arr.size();
        course_tree.insert(course_id, lecture_arr);
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
            int counter = 0;
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
            // In this case we need to go to the course tree and add the lectures that have no views too
            // Create a functor to apply over the lectures that have views:
            class UpdateNotViewedClasses
            {
            public:
                int counter = 0;
                int max_adds;
                int *courses;
                int *classes;

                explicit UpdateNotViewedClasses(int max_adds, int* courses, int* classes) :
                counter(0), max_adds(max_adds), courses(courses), classes(classes) { }
                void operator()(const std::shared_ptr<graph_node<int, Array<std::shared_ptr<graph_node<LectureContainer, int>>>>>& course)
                {
                    if(counter >= max_adds) // All the numOfClasses lectures are already inserted into the arrays.
                    {
                        return;
                    }
                    // Check each one of the lectures in the course and add it to the arrays if it has no views:
                    for(int i = 0; i < (course->val).size(); i++)
                    {
                        if(course->val[i] == nullptr)
                        {
                            // Insert the class into the arrays:
                            courses[counter] = course->key;
                            classes[counter] = i;
                            counter++;
                            if(counter >= max_adds) // If this was the last class to add, stop inserting to the arrays.
                            {
                                return;
                            }
                        }
                    }
                }
            };
            int remaining_classes = numOfClasses - (views_functor.counter);
            UpdateNotViewedClasses no_views_functor(remaining_classes, courses, classes);
            course_tree.inOrder(no_views_functor, remaining_classes); // In the worst case each course has exactly one class.
        }
        return true;
    }
}