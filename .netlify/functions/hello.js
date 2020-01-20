const fs = require('fs');
const util = require('util');

const readFile = util.promisify(fs.readFile);

exports.handler = async function(event, context) {
  const buffer = await readFile("./hello.wasm");
  const module = await WebAssembly.compile(buffer);
  const instance = await WebAssembly.instantiate(module);
  return {statusCode : 200, body : "Hello, World " + instance.exports.helloWorld()};
};

