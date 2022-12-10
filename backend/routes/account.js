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



router.put("/withdraw/:id", function (request, response) {
  account.withdraw(request.params.id, request.body, function (err, dbResult) {
    if (err) {
      response.send(err);
    } else {
      if (dbResult.length > 0) {
        response.send(false);
      } else {
        response.send(true);
      }
    }
  });
}

);
router.put("/debit_transfer/:id", function (request, response) {
  account.debit_transfer(request.params.id, request.body, function (err, dbResult) {
    if (err) {
      response.send(err);
    } else {
      if (dbResult.length > 0) {
        response.send(false);
      } else {
        response.send(true);
      }
    }
  });
}
);

module.exports = router;