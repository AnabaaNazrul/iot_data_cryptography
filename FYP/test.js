var CryptoJS = require("crypto-js");
var esp8266_msg = 'cWfLwrddwwuHOOH1NrYUIbOUNK/3O5KCe+RcFCZfRYOr83uQK/PQw3lTHevWYx0R';
var esp8266_iv  = 'UmlvXE4VfHjycZbQZP7a6w==';

// The AES encryption/decryption key to be used.
var AESKey = '2B7E151628AED2A6ABF7158809CF4F3C';

var plain_iv =  new Buffer( esp8266_iv , 'base64').toString('hex');
var iv = CryptoJS.enc.Hex.parse( plain_iv );
var key= CryptoJS.enc.Hex.parse( AESKey );

console.log("Let's ");

// Decrypt
var bytes  = CryptoJS.AES.decrypt( esp8266_msg, key , { iv: iv} );
var plaintext = bytes.toString(CryptoJS.enc.Base64);
var decoded_b64msg =  new Buffer(plaintext , 'base64').toString('ascii');
var decoded_msg =     new Buffer( decoded_b64msg , 'base64').toString('ascii');

console.log("Decryptedage: ", decoded_msg);