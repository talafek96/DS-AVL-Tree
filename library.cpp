#include "library.h"
#include "Boom.h"

using namespace DS;

void* Init()
{
    Boom* DS;
    try
    {
        DS = new Boom();
    }
    catch(const std::bad_alloc& e)
    {
        DS = NULL;
    }
    return (void*)DS;
}

StatusType AddCourse(void *DS, int courseID, int numOfClasses)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    bool res;
    try
    {
        res = static_cast<Boom*>(DS)->addCourse(courseID, numOfClasses);
    }
    catch(const Boom::InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    if(!res)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCourse(void *DS, int courseID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    bool res;
    try
    {
        res = static_cast<Boom*>(DS)->removeCourse(courseID);
    }
    catch(const Boom::InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    if(!res)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    bool res;
    try
    {
        res = static_cast<Boom*>(DS)->watchClass(courseID, classID, time);
    }
    catch(const Boom::InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    if(!res)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int* timeViewed)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    bool res;
    try
    {
        res = static_cast<Boom*>(DS)->timeViewed(courseID, classID, timeViewed);
    }
    catch(const Boom::InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    if(!res)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int* courses, int* classes)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    bool res;
    try
    {
        res = static_cast<Boom*>(DS)->getMostViewedClasses(numOfClasses, courses, classes);
    }
    catch(const Boom::InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    if(!res)
    {
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void **DS)
{
    if(!DS)
    {
        return;
    }
    delete static_cast<Boom*>(*DS);
    *DS = NULL;
}