#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int index = 0; index < candidate_count; index += 1)
    {
        int aux = 0;
        string candidate_atual = candidates[index].name;
        for (int i = 0; candidate_atual[i] != '\0'; i += 1)
        {
            if (candidate_atual[i] != name[i])
            {
                aux = 1;
            }
        }

        if (aux == 0)
        {
            preferences[voter][rank] = index;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int index = 0; index < voter_count; index += 1)
    {
        for (int j = 0; j < candidate_count; j += 1)
        {
            int vote = preferences[index][j];
            if (!candidates[vote].eliminated)
            {
                candidates[vote].votes += 1;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // voter_count
    int max = 0;
    int index = 0;
    for (int i = 0; i < candidate_count; i += 1)
    {
        if (!candidates[i].eliminated)
        {
           max = candidates[i].votes;
           index = i;
           break;
        }
    }

    for (int i = 0; i < candidate_count; i += 1)
    {
        if (!candidates[i].eliminated)
        {
           if (candidates[i].votes > max)
           {
               max = candidates[i].votes;
               index = i;
           }
        }
    }

    for (int i = 0; i < candidate_count; i += 1)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes == max && i != index)
            {
                return false;
            }
        }
    }

    float min_votes = round((float)voter_count / (float)2);

    if (candidates[index].votes >= min_votes)
    {
        fprintf(stdout, "%s\n", candidates[index].name);
        return true;
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = 0;
    for (int i = 0; i < candidate_count; i += 1)
    {
        if (!candidates[i].eliminated)
        {
           min = candidates[i].votes;
           break;
        }
    }

    for (int i = 0; i < candidate_count; i += 1)
    {
        if (!candidates[i].eliminated)
        {
           if (candidates[i].votes < min)
           {
               min = candidates[i].votes;
           }
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int online = 0;
    for (int i = 0; i < candidate_count; i += 1)
    {
        if (!candidates[i].eliminated)
        {
            online += 1;
        }
    }

    if (online == 1)
    {
        return false;
    }

    for (int index = 0; index < candidate_count; index += 1)
    {
        if (!candidates[index].eliminated)
        {
            if (candidates[index].votes > min)
            {
                return false;
            }
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int index = 0; index < candidate_count; index += 1)
    {
        if (!candidates[index].eliminated)
        {
            if (candidates[index].votes == min)
            {
                candidates[index].eliminated = true;
            }
        }
    }
    return;
}
