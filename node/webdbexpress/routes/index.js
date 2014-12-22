
/*
 * GET home page.
 */

exports.index = function(req, res){
  res.render('index', { title: 'Express' });
};

exports.sample1 = function(req, res) {
    var id = req.param('id');
    res.render('foo', {
        title: 'webdb sample',
        var1: 'dog',
        var2: 'cat',
        var3: req.param('id')
    });
};

// Connect to the MongoDB
var mongo = require('mongodb');
var client = new mongo.Db('test', 
        new mongo.Server('127.0.0.1', 27017));
console.log(client);
client.open(function(err, client) {
    if(err) {
        console.log(err);
    } else {
        console.log('connected to mongodb');
    }
});

// Show data and form
exports.showMongo = function(req, res) {
    client.collection('webdbtest',
        function(err, collection) {
            if(err) {
                throw err;
            }
            collection.find().toArray(
                function(err, results) {
                    if(err) {
                        throw err;
                    }
                    res.render('mongo', {
                        title: 'Mongo Example',
                        list: results
                    });
                });
        });
};

// Save posted data
exports.saveMongo = function(req, res) {
    var name = req.param('name');
    client.collection('webdbtest',
        function(err, collection) {
            if(err) {
                throw err;
            }
            collection.save({name: name}, function(err) {
                if(err) {
                    throw err;
                }
                res.redirect('/mongo');
            });
        }
    );
};

// mvc test
exports.mvc = function(req, res) {
    var icecreamList = [
        {id: 1, name: 'vanilla'},
        {id: 2, name: 'orange'},
        {id: 3, name: 'lemon'},
    ];
    res.render('mvc', {
              title: 'Client MVC Test',
              icecreamList: icecreamList,
    });
};

// sample of Backbone.js 
exports.backboneSample = function(req, res) {
    res.render('backboneSample');
};

// sample of require.js
exports.requireSample = function(req, res) {
    res.render('requireSample');
};
