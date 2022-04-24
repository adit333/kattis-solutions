/*https://ualberta.kattis.com/sessions/x2xwog/problems/fantasydraft
*/

#include <bits/stdc++.h>

using namespace std;

void fantasy_draft(int num_owners, int team_size, vector<vector<string>> &owner_preferences,
        map<string, int> &player_rank_map, map<int, string> &available_players) {
    // Simulate Fantasy Draft Picks
    vector<vector<string>> selected_players(num_owners);

    for (int pick_num = 0; pick_num < team_size; ++ pick_num) {
        for (int owner = 0; owner < num_owners; ++owner) {
            bool has_picked = false;
            while (!has_picked && owner_preferences[owner].size() > 0) {
                string prefered_player = owner_preferences[owner].back();
                int preferred_player_rank = player_rank_map[prefered_player];
                owner_preferences[owner].pop_back();

                if (available_players.count(preferred_player_rank) > 0) {
                    selected_players[owner].push_back(prefered_player);
                    available_players.erase(preferred_player_rank);
                    has_picked = true;
                }
            }

            if (!has_picked) {
                string player_name = available_players.begin()->second;
                selected_players[owner].push_back(player_name);
                int player_rank = available_players.begin()->first;
                available_players.erase(player_rank);
            }
        }
    }

    for (auto owner_selections : selected_players) {
        for (auto player : owner_selections) {
            cout << player << " ";
        }
        cout << endl;
    }
}

int main() {
    int num_owners, team_size;
    cin >> num_owners >> team_size;

    // Read owner preferences
    vector<vector<string>> owner_preferences(num_owners);
    for (auto &pref: owner_preferences) {
        int num_of_preferences;
        cin >> num_of_preferences;
        for (int i = 0; i < num_of_preferences; ++i) {
            string player_name;
            cin >> player_name;
            pref.push_back(player_name);
        }
        reverse(pref.begin(), pref.end());
    }

    // Read plyer rankings
    map<string, int> player_rank_map;
    map<int, string> available_players;

    int num_of_players;
    cin >> num_of_players;
    for (int rank = 0; rank < num_of_players; ++rank) {
        string player_name;
        cin >> player_name;

        player_rank_map[player_name] = rank;
        available_players[rank] = player_name;
    }
    fantasy_draft(num_owners, team_size, owner_preferences, player_rank_map, available_players);
}
