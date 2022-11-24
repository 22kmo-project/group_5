const db = require('../database');


const customer = {
    getById: function(id, callback) {
      return db.query('select * from customer where idcustomer = ?', [id], callback);
    },


    getAll: function(callback) {
      return db.query('select * from customer', callback);
    },


    add: function(add_data, callback) {
      return db.query(
        'insert into customer (idcustomer, customername, address, phonenumber) values(?,?,?,?)',
        [add_data.idcustomer, add_data.customername, add_data.address, add_data.phonenumber],
        callback
      );
    },


    delete: function(id, callback) {
      return db.query('delete from customer where idcustomer=?', [id], callback);
    },

    
    update: function(id, customer, callback) {
      return db.query(
        'update customer set idcustomer=?, customername=?, address=?, phonenumber=?, where idcustomer=?',
        [customer.idcustomer, customer.customername, customer.address, customer.phonenumber, id],
        callback
      );
    }
  };
  module.exports = customer;