/**
 * @return {string}
 */
function BuildMouseInfo(e,element,mType) {
    let x = e.pageX - element.offsetLeft + 1;
    let y = e.pageY - element.offsetTop + 1;

    x <<= 16;
    y <<= 16;

    x /= element.width;
    y /= element.height;

    let Msg = {};
    Msg.type = "ControlOrder";

    let data = {};
    data.type = mType;
    data.x = parseInt(x);
    data.y = parseInt(y);

    if(data.type === "MiddleButtonWheel")
    {
        if(e.deltaY > 0)
        {
            data.info = parseInt(-120);
        }
        else if(e.deltaY < 0)
        {
            data.info = parseInt(120);
        }
        else
        {
            console.log("deltaY unknown");
        }
        
        console.log(e);
    }

    Msg.data = data;


    return JSON.stringify(Msg);
}

function SendMouseEvent(e,element,mType) {
    if(MasterInfo.Controlling !== 1) return;

    MasterInfo.SocketClient.send(BuildMouseInfo(e,element,mType));
}

function mmevent(e,element)
{
    SendMouseEvent(e,element,"MouseMove");
}

function mdevent(e,element) {
    let btn = e.button;

    if(btn === 0)
    {
        SendMouseEvent(e,element,"LeftButtonDown");
    }
    else if (btn === 1)
    {
        SendMouseEvent(e,element,"MiddleButtonDown");
    }
    else if (btn === 2)
    {
        SendMouseEvent(e,element,"RightButtonDown");
    }
}

function muevent(e,element){
    let btn = e.button;

    if(btn === 0)
    {
        SendMouseEvent(e,element,"LeftButtonUp");
    }
    else if (btn === 1)
    {
        SendMouseEvent(e,element,"MiddleButtonUp");
    }
    else if (btn === 2)
    {
        SendMouseEvent(e,element,"RightButtonUp");
    }
}

function mwevent(e,element) {
    SendMouseEvent(e,element,"MiddleButtonWheel");
}

function kdevent(e) {
    let keynum;

    if(window.event)
    {
        keynum = e.keyCode
    }
    else if(e.which)
    {
        keynum = e.which
    }

    let Msg = {};
    Msg.type = "ControlOrder";

    let data = {};
    data.type = "KeyboardDown";
    data.key = keynum;
    Msg.data = data;

    MasterInfo.SocketClient.send(JSON.stringify(Msg));
}

function kuevent(e){
    let keynum;

    if(window.event)
    {
        keynum = e.keyCode
    }
    else if(e.which)
    {
        keynum = e.which
    }

    let Msg = {};
    Msg.type = "ControlOrder";

    let data = {};
    data.type = "KeyboardUp";
    data.key = keynum;
    Msg.data = data;

    MasterInfo.SocketClient.send(JSON.stringify(Msg));
}
