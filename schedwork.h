#ifndef SCHEDWORK_H
#define SCHEDWORK_H

#ifndef RECCHECK
#include <vector>
#endif

// type for the ID of a worker
typedef unsigned int Worker_T;
// n-by-k Matrix of each of the k workers' availability over an n-day period
typedef std::vector<std::vector<bool>> AvailabilityMatrix;

// n-by-d matrix with the d worker IDs who are scheduled 
// to work on each of the n days
typedef std::vector<std::vector<Worker_T> > DailySchedule;

/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 * 
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over 
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);
/**
 * @brief Checks if a worker can be scheduled on a given day
 * 
 * This function verifies if a worker can be scheduled for a particular
 * day by checking:
 * - Worker's availability on that day
 * - Worker's current shift count against max allowed shifts
 * - Worker's presence in current day's schedule
 * 
 * @param [in] avail The availability matrix
 * @param [in] sched The current schedule
 * @param [in] shifts Array tracking number of shifts for each worker
 * @param [in] day The day to check
 * @param [in] worker The worker to check
 * @param [in] maxShifts Maximum allowed shifts for any worker
 * @return true if worker can be scheduled, false otherwise
 */
bool canScheduleWorker(const AvailabilityMatrix& avail, const DailySchedule& sched,
    const std::vector<size_t>& shifts, size_t day, Worker_T worker,
    size_t maxShifts);

/**
* @brief Recursively finds a valid work schedule
* 
* This function uses backtracking to find a valid schedule that meets
* all constraints. It attempts to fill each position in the schedule
* recursively, backtracking when constraints are violated.
* 
* @param [in] avail The availability matrix
* @param [in] dailyNeed Number of workers needed per day
* @param [in] maxShifts Maximum shifts any worker is allowed
* @param [in,out] sched The schedule being constructed
* @param [in,out] shifts Array tracking number of shifts for each worker
* @param [in] day Current day being scheduled
* @param [in] pos Current position within the day being scheduled
* @return true if a valid schedule is found, false otherwise
*/
bool findSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed,
const size_t maxShifts, DailySchedule& sched,
std::vector<size_t>& shifts, size_t day, size_t pos);


#endif