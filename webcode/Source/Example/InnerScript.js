
var InnerScriptInterface = {};

/**
 * @return {boolean}
 */
InnerScriptInterface.IsControlling = function () {
    return MasterInfo.Controlling === 1;
};

/**
 * @return {boolean}
 */
InnerScriptInterface.IsConnected = function(){
    return MasterInfo.Connected === 1;
};

InnerScriptInterface.SocketConnect = function(){
    SocketConnect();
};


mergeInto(LibraryManager.library, InnerScriptInterface);