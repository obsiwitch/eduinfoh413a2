#ifndef TABU_IMPROVEMENT
#define TABU_IMPROVEMENT

#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <random>

#include "TabuSearch/GlobalArgsTabu.hpp"
#include "Improvement.hpp"

/**
 * The TabuImprovement class selects the best scoring Permutation in the given
 * Neighbourhood. A Tabu list is kept to avoid selecting results already visited
 * recently. The maximum number of elements the tabu list can contain is updated
 * during the search and is called the tabu tenure.
 */
class TabuImprovement : public Improvement {
public:
    /**
     * Value by which the tabu tenure should be increased to avoid revisiting
     * candidate solutions.
     * (minor influence)
     */
    static const unsigned TT_INC = 1;
    
    /**
     * Value by which the tabu tenure should be decreased when it has not
     * changed for a sufficient number of iterations
     * (TT_ITERATIONS_WO_MODIFICATION).
     * (minor influence)
     */
    static const unsigned TT_DEC = 1;

    TabuImprovement(const Instance& instance, const GlobalArgsTabu& g);
    
    Permutation improve(Permutation& p, Neighbourhood& n);

private:
    std::deque<Permutation> tabuQueue_;
    
    /**
     * Maximum number of elements the tabu queue can contain. Updated during
     * the search.
     *
     * @see checkRepetitions()
     */
    unsigned tabuTenure_;
    
    /**
     * Keeps the number of encounter of a Permutation in a hash table.
     * The permutation is identified by its score (key). This is an
     * approximation, but it costs less than checking each time all the
     * elements in the Permutation.
     */
    std::unordered_map<int, unsigned> permutationOccurrences_;
    
    /**
     * Keeps the frequently encountered Permutations. Permutations are
     * identified by their score.
     */
    std::unordered_set<int> frequentlyEncountered_;
    
    /**
     * Number of iterations during which no modification has been made to
     * the tabu tenure.
     */
    unsigned ttIterationsNoModif;
    
    /**
     * Random number engine. Initialized with the instance's total sum in order
     * to have the same results between runs for the same instance.
     */
    std::mt19937 gen_;

    /**
     * Best Permutation found by the Tabu Search so far.
     */
    Permutation eliteP_;
    
    /* Begin tabu search parameters - these parameters must be fine tuned
     * (by using irace for example).
     */
        /**
         * Number of iterations during which the tabu tenure has not changed
         * considered sufficient to decrease it.
         */
        unsigned p_ttIterationsWoModification;
        
        /**
         * Maximum occurrences a candidate solutions must attain to be considered
         * frequently encountered;
         */
        unsigned p_maxOccurencesFrequentlyEncountered;
        
        /**
         * Maximum number of candidate solutions frequently encountered. The escape
         * mechanism is triggered if this number is exceeded.
         *
         * @see escape()
         */
        unsigned p_maxCandidateTriggerEscape;
        
        /**
         * Value used in the escape mechanism to determine the maximum number of
         * successive random changes which will be applied to the current
         * Permutation.
         *
         * @see escape()
         */
        unsigned p_randomStepsEscape;
    /* End tabu search parameters */

    Permutation stepTabuSearch(Permutation& p, Neighbourhood& n);
    bool checkRepetitions(Permutation& newP);
    Permutation escape(Permutation& p);
    
    void updateTabuQueue(Permutation& p);
    void updateElite(Permutation& newP);
};

#endif // TABU_IMPROVEMENT
