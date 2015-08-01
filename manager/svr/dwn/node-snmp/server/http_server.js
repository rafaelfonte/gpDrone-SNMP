var snmp = require('../node-snmp-native/lib/snmp');
var http = require('http');


var host = '143.54.12.76';
var community = 'public';

var session = new snmp.Session({ host: host, community: community });

var result = "";

var dictionary = 
	{"sysAircraftID" : ".1.1",
	 "sysAircraftType" : ".1.2",
	 "sysTimeUp" : ".1.4",
	 "instPosGpsLatitude" : ".2.1.5",
	 "instPosGpsLongitude" : ".2.1.6",
	 "instPosAltitude" : ".2.1.7",
	 "instClTime" : ".2.2.1",
	 "instSpeedGround" : ".2.3.3",
	 "instSpeedVertical" : ".2.3.4",
	 "lightNum" : ".5.1",
	 "lightIndex" : ".5.2.1.1",
	 "lightDescription" : ".5.2.1.2",
	 "lightToggle" : ".5.2.1.3",
	 "lgSetPosition" : ".7.3",
	 "instTotalFuel" : ".2.5"
	};

var app = http.createServer(function (req, res) {
	res.setHeader('Content-Type', 'application/json');
	
	var request = req.url.split("/");
	if(request.length < 3){
		res.end(JSON.stringify({res : "??"}));
		return;
	}
	console.log(request)
	var t_req = request[1];
	var obj_req = request[2].split(".")[0];
	var obj_idx = request[2].split(".")[1];
	console.log("type is " + t_req + ", obj is " + obj_req + ", idx is " + obj_idx);
	
	
	if(t_req == "GET"){		
		session.get({oid : '.1.3.6.1.4.1.12620' + dictionary[obj_req] + "." + obj_idx}, function(err,varbinds){
			if(err){
				console.log(err);
			} else {
				vb = varbinds[0];
				result = vb.value;
				console.log("Result is " + result);
				res.end(JSON.stringify({res : result}));
			}
		});
	}
	else{//It's a set!
		session.set({ oid : '.1.3.6.1.4.1.12620' + dictionary[obj_req] + "." + obj_idx, value: request[3], type: 2}, function (error, varbind) {
		    if (error) {
			console.log('Fail :(');
			res.end(JSON.stringify({res : result}));
		    } else {
			console.log('The set is done.');
			res.end(JSON.stringify({res : result}));
		    }
		});
	}
}).listen(1337, '127.0.0.1');

console.log('Server running at http://127.0.0.1:1337/');
/*
var number = 0;
function reset(){
	number = number + 1;
	document  = "<html><head><script type=\"text/javascript\">setTimeout(function(){location.reload(true)},1000);</script></head><body>" + number + "</body></html>";
}

setInterval(reset,100);
*/
