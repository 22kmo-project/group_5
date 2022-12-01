const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');


router.post('/', 
  function(request, response) {
    if(request.body.idcard && request.body.password){
      const idcard = request.body.idcard;
      const password = request.body.password;
      console.log("\nTunnukset: " + idcard + " " + password);
      
        card.checkPassword(idcard, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(password,dbResult[0].password, function(err,compareResult) {
                console.log("tunnusluku: " + dbResult[0].password);
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ card: idcard });
                  response.send(token);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("card unknown");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("idcard or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(idcard) {
  dotenv.config();
  return jwt.sign(idcard, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;