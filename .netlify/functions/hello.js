const fs = require('fs');
const path = require('path');
const util = require('util');

const readFile = util.promisify(fs.readFile);

exports.handler = async function(event, context) {
  const buffer = await readFile(path.join(__dirname, "hello.wasm"));
  const module = await WebAssembly.compile(buffer);
  const instance = await WebAssembly.instantiate(module);
  return {statusCode : 200, body : "Hello, World " + instance.exports.helloWorld()};
};

exports.handler().then(console.log);

