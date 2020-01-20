const fs = require('fs');
const path = require('path');
const util = require('util');
const https = require('https');
const url = require('url');

const readFile = util.promisify(fs.readFile);

function loadFile(link, callback) {
  https.get(url.parse(link), function (res) {
      if (200 !== res.statusCode) {
        res.setEncoding('utf8');
        let data = '';
        res.on('data', (strData) => {
          data += strData;
        });
        res.on('end', () => {
          if (!res.complete) {
            callback('Server error, incomplete response: ' + data, null);
          } else {
            callback('Server error, response: ' + data, null);
          }
        });
      } else {
        res.setEncoding('binary');
        let chunks = [];

        res.on('data', function(chunk) {
            chunks.push(Buffer.from(chunk, 'binary'));
        });

        res.on('end', function() {
            callback(null, Buffer.concat(chunks));
        });
      }
  });
}

exports.handler = async function(event, context) {
  const buffer = await util.promisify(loadFile)("https://bkase.dev/static/wasm/hello.wasm");
  const module = await WebAssembly.compile(buffer);
  const instance = await WebAssembly.instantiate(module);
  return {statusCode : 200, body : "Hello, World " + instance.exports.helloWorld()};
};

// exports.handler().then(console.log);

