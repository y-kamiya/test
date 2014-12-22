define(['config', 'util'], function(config, util) {
    var component = function() {
        config.console();
        util.console();
    }
    return {
        console: component,
    };
});
