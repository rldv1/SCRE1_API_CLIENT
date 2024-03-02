// i so hate js and ts like pizdec nahui, shittiest shit could i ever seen
const axios = require('axios');

async function test(API_URL) {
    const type = "spectate"; // team, scid_requests, ...
    const payload = { key: "ENTER_YOUR_KEY_HERE", type: type, tag: "#2PP" };

    try {
        const response = await axios.get(API_URL + "/launch", { params: payload });
        return response.data;
    } catch (error) {
        console.error("blyat pizdec nahui suka", error);
        process.exit(1);
    }
}

async function main() {
    const SERVERS_LIST_URL = "https://raw.githubusercontent.com/rldv1/SCRE1_API_CLIENT/main/actual_nodes_prod.json";
    console.log("DL Server list from: %s", SERVERS_LIST_URL);

    try {
        const response = await axios.get(SERVERS_LIST_URL);
        const servers = response.data;
        const selectedServer = servers.api_nodes[Math.floor(Math.random() * servers.api_nodes.length)];

        console.log("Picked API: %s", selectedServer[1]);
        const API_URL = "http://" + selectedServer[0];

        console.log(await test(API_URL));
        // {"success": True, "uses_left": 666, .....}
        // {"success": False, "reason": "flood_wait", "try_after": 66, .....}
    } catch (error) {
        console.error("Error:", error);
    }
}

main();
