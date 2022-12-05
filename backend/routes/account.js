const express = require('express');
const router = express.Router();
const account = require('../models/account_model');

router.get('/:id?',
function(request,response){
  if (request.params.id){
    account.getById(request.params.id, function(err, dbResult){
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  } else {
    account.getAll(function(err, dbResult){
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
});

router.post('/', 
function(request, response) {
  account.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  account.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  account.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.post('/withdraw', 
function(request, response) {
  account.cashWithdraw(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      if (dbResult[0][0]["success"] == 1) { 
        console.log(dbResult[0]);
        console.log("Rahat tulossa!\n");
        response.json(dbResult[0]);
      } else {
        console.log(dbResult[0]);
        console.log("Saldo ei riitä\n");
        response.json(dbResult[0]);
      }
    }
  });
});

module.exports = router;