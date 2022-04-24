/*https://ualberta.kattis.com/sessions/jtoinb/problems/watchlater

Approach: Dynamic Programming

Let S be the set of remaining video types to watch
Let f(S) be the min no. of clicks needed to watch all of S
Let clicks[t] be th no. of clicks needed to watch videos of type t first in a given set S,
    this is simply the no. of chunks of that vidoe type.
Recurrence:
f(S) = 0                                    if S is empty
     = min{t in S} (clicks[t] + f(S-t))     otherwise;  where t is a type of a video
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_VID_TYPES = 20;
int memo[1<<MAX_VID_TYPES];                 // There are max 20 vidoe types, so at most 2^20 subsets of video types
//unordered_map<char, int> video_type_ids;  // Simply id each vidoe type as ints
int video_type_ids[256];    // Since the ASCII code for letters can go up to a mazx of 256


int min_clicks(int remaining_video_types, string watch_list) {
    /* remaining_video_types is a subset S of video type that we have to watch
        We will interpret it in binary, so 3(dec) = 11(bin) means that video types with id 0 & 1 are left
    */

    if (remaining_video_types == 0)
        return 0;

    if (memo[remaining_video_types] != -1)
        return memo[remaining_video_types];

    // Calculate clicks[t], i.e., the no. of clicks it takes to watch videos of type only
    // to count clicks[i], we simply count the no. of consecutive chunks of that video type
    int clicks[MAX_VID_TYPES] = {0};
    int previous_video_type_id = -1;
    for (char video_type : watch_list) {
        int video_type_id = video_type_ids[video_type];
        if (remaining_video_types & (1<<video_type_id)) {
            if (video_type_id != previous_video_type_id)
                ++clicks[video_type_id];
            previous_video_type_id = video_type_id;
        }
    }

    // Now compute min no. of clicks for thise subset of vidoes by trying each video type as
    // first one to watch and then simply choosing the minimum
    memo[remaining_video_types] = 10000000; // alarge val to represent infinity
    for (int video_type_id = 0; video_type_id < MAX_VID_TYPES; ++video_type_id) {
          if (remaining_video_types & (1<<video_type_id))
                memo[remaining_video_types] = min(
                    clicks[video_type_id] + min_clicks(remaining_video_types^(1<<video_type_id), watch_list),
                    memo[remaining_video_types]
                );
    }
    return memo[remaining_video_types];
}


void watch_later(int num_of_vidoes_in_watch_list,
        int num_of_video_types, string watch_list) {
    memset(memo, -1, sizeof(memo));
    memset(video_type_ids, -1, sizeof(video_type_ids));

    int id = 0;
    for (char video_type: watch_list) {
        if (video_type_ids[video_type] == -1)
            video_type_ids[video_type] = id++;
    }
    cout << min_clicks((1<<num_of_video_types)-1, watch_list) << endl;
}

int main() {
    int num_of_videos_in_watch_list, num_of_video_types;
    cin >> num_of_videos_in_watch_list >> num_of_video_types;
    string watch_list;
    cin >> watch_list;
    watch_later(num_of_videos_in_watch_list, num_of_video_types, watch_list);
}