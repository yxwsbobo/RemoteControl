
var MasterInfo = {};
MasterInfo.Controlling = 0;
MasterInfo.Connected = 0;


function StartInit()
{
    let canvasVideo = document.getElementById("canvas");
    canvasVideo.tabIndex = 1000;
}

function GetVideoInfo() {
    let Info = {};
    Info.width = 1280;
    Info.height = 720;
    Info.bitRate = 4000000;
    Info.frameRate = 20;
    return Info;
}

function ControlRemote(cName, VideoInfo) {
    if (!MasterInfo.Connected) return;

    let OnStop = ()=>{
        let Msg = {};
        Msg.type = "ControlMachine";
        Msg.data = VideoInfo;
        Msg.data.name = cName;

        MasterInfo.SocketClient.send(JSON.stringify(Msg));
    };

    StopControl(OnStop);
}

function RefreshControlledList() {
    if (!MasterInfo.Connected) return;

    let Msg = {};
    Msg.type = "ListControlled";
    MasterInfo.SocketClient.send(JSON.stringify(Msg));
}

function StopControl(callBack) {
    MasterInfo.Controlling = 0;
    let Msg = {};
    Msg.type = "StopControl";

    MasterInfo.SocketClient.send(JSON.stringify(Msg));


    //Need Wait Stop finished
    _InitPlayer();
    callBack();
}

function SocketConnect() {
    MasterInfo.SocketClient = new WebSocket("ws://" + window.location.host + ":5656");

    MasterInfo.SocketClient.binaryType = "arraybuffer";

    MasterInfo.SocketClient.onopen = ()=> {
        MasterInfo.Connected = 1;
        console.log("WebSocket Opened");

        MasterInfo.SocketClient.send(JSON.stringify({type: "RegistMaster"}));
        RefreshControlledList();
        _OnSocketConnected();


    };

    MasterInfo.SocketClient.onclose = ()=> {
        MasterInfo.Connected = 0;
        MasterInfo.Controlling = 0;

        _InitPlayer();
        _OnSocketClosed();

        console.log("WebSocket Closed");
    };

    MasterInfo.SocketClient.onmessage = (evt)=> {
        if (evt.data instanceof ArrayBuffer) {
            let offset = _GetVideoBuffer();
            Module.HEAP8.set(new Uint8Array(evt.data), offset);
            _SocketMessage(offset, evt.data.byteLength);
            return;
        }

        console.log("Receive Msg :", evt.data);
        let Msg = JSON.parse(evt.data);

        if (Msg.type === "ControlledList") {
            FillControlledList(Msg.data);
        }
        else if (Msg.type === "ControlledChanged") {
            ControlledListChanged(Msg["data"].name, Msg["data"].state);
        }
        else if (Msg.type === "ControlMachineResult") {
            if (Msg.data["success"] === 1) {
                console.log("Control Success!");
                MasterInfo.Controlling = 1;
            }
            else {
                MasterInfo.Controlling = 0;
                console.log("Control Failed!");
            }
        }

    };

    MasterInfo.SocketClient.onerror = ()=> {
        console.log("webSocket on error");
    }
}

function FillControlledList(ItemLists){
    let mList = document.getElementById("MachineLists");
    while (mList.length > 0) {
        mList.remove(0);
    }

    let VideoInfo = GetVideoInfo();

    for (const mItem of ItemLists) {
        let nItem = document.createElement("option");
        nItem.text = mItem.name;
        nItem.onclick = ()=> ControlRemote(mItem.name,VideoInfo);
        mList.add(nItem);
    }

}

function ControlledListChanged(name, state) {
    let mList = document.getElementById("MachineLists").options;

    if(state === 1)
    {
        let nItem = document.createElement("option");
        nItem.text = name;
        nItem.onclick = ()=> ControlRemote(name,GetVideoInfo());
        mList.add(nItem);
    }
    else
    {
        for (let index = 0; index < mList.length; index++) {
            if(mList[index].text === name)
            {
                mList.remove(index);
                break;
            }
        }
    }
    // if(mList.length == 0)
    // {
    //   document.getElementById("MachineLists").hidden();
    // }
    // else
    // {
    //   document.getElementById("MachineLists")
    // }
}