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

    add: function(add_data, callback) {
      return db.query(
        'insert into customer (idcustomer, customername, address, phonenumber) values(?,?,?,?)',
        [add_data.idcustomer, add_data.customername, add_data.address, add_data.phonenumber],

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
      return db.query('delete from customer where idcustomer=?', [id], callback);
    },

    
    update: function(id, customer, callback) {
      return db.query(
        'update customer set customername=?, address=?, phonenumber=?, where idcustomer=?',
        [customer.customername, customer.address, customer.phonenumber, id],
        callback
      );
    }
  };
  module.exports = customer;