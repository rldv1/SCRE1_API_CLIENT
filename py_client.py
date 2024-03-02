import requests, json, random

def test(API_URL):
    

    type = "spectate" # team, scid_requests, ...
    payload = {"key": "ENTER_YOUR_KEY_HERE", "type": type, "tag": "#2PP"}
    
    try:
        response = requests.get(API_URL + "/launch", params=payload)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        print("blyat pizdec nahui suka", e)
        exit(1)

if __name__ == "__main__":  
    SERVERS_LIST_URL = "https://raw.githubusercontent.com/rldv1/SCRE1_API_CLIENT/main/actual_nodes_prod.json"
    print("DL Server list from: %s" % SERVERS_LIST_URL)
    
    SELECTED_SERVER = random.choice(requests.get(SERVERS_LIST_URL).json()["api_nodes"])
    
    print("Picked API: %s" % SELECTED_SERVER[1])
    API_URL = "http://" + SELECTED_SERVER[0]
    
    print(test(API_URL))
    # {"success": True, "uses_left": 666, .....}
    # {"success": False, "reason": "flood_wait", "try_after": 66, .....}