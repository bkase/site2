const fs = require('fs');

exports.handler = async function(event, context) {
  const buffer = await fs.readFile("./hello.wasm");
  const module = await WebAssembly.compile(buffer);
  const instance = await WebAssembly.instantiate(module);
  callback(null, {statusCode : 200, body : "Hello, World " + instance.exports.helloWorld()});
};
