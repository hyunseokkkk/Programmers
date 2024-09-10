#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// solution 함수 정의
string solution(string video_len, string pos, string op_start, string op_end, vector<string> commands) {
    string answer = "";
    
    stringstream ss(video_len);
    
    int min = 0, sec = 0; 
    int len = 0;
    int start_min = 0, start_sec = 0, start_len = 0;
    char colon;
    
    // 비디오 전체 길이 계산
    ss >> min >> colon >> sec; 
    len = min * 60 + sec; 
    
    ss.clear();
    ss.str(pos);
    
    // 현재 위치 계산
    ss >> start_min >> colon >> start_sec;
    start_len = start_min * 60 + start_sec;
    
    // 오프닝 시작 위치 계산
    int op_s_min = 0, op_s_sec = 0, op_s_len = 0;
    ss.clear();
    ss.str(op_start);
    ss >> op_s_min >> colon >> op_s_sec;
    op_s_len = op_s_min * 60 + op_s_sec;
    
    // 오프닝 끝 위치 계산
    int op_e_min = 0, op_e_sec = 0, op_e_len = 0;
    ss.clear();
    ss.str(op_end);
    ss >> op_e_min >> colon >> op_e_sec;
    op_e_len = op_e_min * 60 + op_e_sec;
    
          // 각 명령 실행 후 오프닝 구간에 있으면 오프닝 끝으로 이동
        if (start_len >= op_s_len && start_len <= op_e_len) {
            start_len = op_e_len;
        }
    // 명령어 처리
    for (string a : commands) {
        if (a == "next") {
            start_len += 10;  // 10초 앞으로 이동
            if (start_len > len) start_len = len;  // 비디오 끝을 넘지 않게
        } else if (a == "prev") {
            start_len -= 10;  // 10초 뒤로 이동
            if (start_len < 0) start_len = 0;  // 0보다 작아지지 않게
        }
        
        // 각 명령 실행 후 오프닝 구간에 있으면 오프닝 끝으로 이동
        if (start_len >= op_s_len && start_len <= op_e_len) {
            start_len = op_e_len;
        }
    }
    
    // 최종 시간 계산
    int final_min = start_len / 60;
    int final_sec = start_len % 60;
    
    // 시간 문자열 포맷
    stringstream oss;
    oss << setw(2) << setfill('0') << final_min << ':' << setw(2) << setfill('0') << final_sec;
    answer = oss.str();
    
    return answer;
}