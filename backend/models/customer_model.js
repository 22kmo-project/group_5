const db = require('../database');


const customer = {
    getById: function(id, callback) {
      return db.query('select * from customer where idcustomer = ?', [id], callback);
    },


    getAll: function(callback) {
      return db.query('select * from customer', callback);
    },


    add: function(card, callback) {
      return db.query(
        'insert into customer (idcustomer, customername, address, phonenumber) values(?,?,?,?)',
        [customer.idcustomer, customer.customername, customer.address, customer.phonenumber],
        callback
      );
    },


    delete: function(id, callback) {
      return db.query('delete from customer where idcustomer = ?', [id], callback);
    },

    
    update: function(id, card, callback) {
      return db.query(
        'update customer set phonenumber = ? where idcustomer = ?',
        [customer.phone_number, id],
        callback
      );
    }
  };
  module.exports = customer;