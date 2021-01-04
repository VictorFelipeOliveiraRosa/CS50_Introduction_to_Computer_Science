#include <cs50.h>
#include <string.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i += 1)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            if (rank > 0)
            {
                for (int j = 0; j < rank; j += 1)
                {
                    if (ranks[j] == i)
                    {
                        return false;
                    }
                }
            }
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks

void record_preferences(int ranks[])
{
    // preferences[MAX][MAX]
    // candidate_count

    for (int i = 0; i < candidate_count - 1; i += 1)
    {
        int index = ranks[i];
        for (int j = i + 1; j < candidate_count; j += 1)
        {
            int vote = ranks[j];
            preferences[index][vote] += 1;
        }
    }

    for (int i = 0; i < candidate_count; i += 1)
    {
        for (int j = 0; j < candidate_count; j += 1)
        {
            printf("[ %d ] ", preferences[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i += 1)
    {
        for (int j = 0; j < candidate_count; j += 1)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i += 1)
    {
        int first_margin_winner = preferences[pairs[i].winner][pairs[i].loser];
        int first_margin_loser = preferences[pairs[i].loser][pairs[i].winner];
        int first_margin = first_margin_winner - first_margin_loser;

        for (int j = i; j < pair_count; j += 1)
        {
            int second_margin_winner = preferences[pairs[j].winner][pairs[j].loser];
            int second_margin_loser = preferences[pairs[j].loser][pairs[j].winner];
            int second_margin = second_margin_winner - second_margin_loser;

            if (second_margin > first_margin)
            {
                pair p = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = p;
            }
        }
    }
    return;
}

bool cycle_verify(int parent, int child, bool visited[])
{

    if (visited[child])
    {
        return true;
    }

    visited[child] = true;

    for (int i = 0; i < candidate_count; i += 1)
    {
    }

    for (int i = 0; i < pair_count; i += 1)
    {
        if (pairs[i].winner == child)
        {
            int parents = child;
            int childs = pairs[i].loser;
            if (locked[parents][childs] && cycle_verify(parents, childs, visited))
            {
                return true;
            }

        }
    }
    return false;
}

bool has_cycle(int parent, int child)
{
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i += 1)
    {
        visited[i] = false;
    }

    return cycle_verify(parent, child, visited);
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i += 1)
    {
        int parent = pairs[i].winner;
        int child = pairs[i].loser;
        locked[parent][child] = true;
        if (has_cycle(parent, child))
        {
            locked[parent][child] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    bool winner = true;
    int winner_index = 0;

    for (int i = 0; i < candidate_count; i += 1)
    {
        winner = true;
        for (int j = 0; j < candidate_count; j += 1)
        {
            if (locked[j][i] == true)
            {
                winner = false;
                break;
            }
        }
        if (winner == true)
        {
            winner_index = i;
            break;
        }
    }
    if (winner == true)
    {
        printf("Is winner -> %s\n", candidates[winner_index]);
    }
    return;
}
