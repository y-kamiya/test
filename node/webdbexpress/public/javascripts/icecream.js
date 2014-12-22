var icecreamModel = {
    list : [
        { id: 1, name: 'vanilla' },
        { id: 2, name: 'orange' },
        { id: 3, name: 'lemon' },
        { id: 4, name: 'coke' },
    ],
    getAll: function getAll() {
        return this.list;
    },
    getIcecreamById: function getIcecreamById(id) {
        var greped = $.grep(this.list, function(entry) {
            return entry.id === parseInt(id);
        });
        console.log('greped ', greped);
        return greped[0];
    },
};

var selectionModel = {
    list: [],
    max: 2,
    add: function(item) {
        var list = this.list;
        list.push(item);
        if (this.max < list.length) {
            list.shift();
        }
        this.updateView();
    },
    getIcecreams: function getIcecreams() {
        return this.list;
    },
    contain: function contain(item) {
        console.log('$$$$$$$$$$$$$$$$$$$ this.list, item', this.list, item);
        return this.list.indexOf(item) >= 0;
    },
    containById: function containById(id) {
        console.log('containById id', id);
        return this.contain(icecreamModel.getIcecreamById(id));
    },
    updateView: function updateView() {
        updateSelection();
        updateSelectedList();
    },
};


// view
function updateSelection() {
    $('#icecreams input[type="checkbox"]').each(function(i, entry) {
        console.log('$$$$$$$$$$ entry.name', entry.name);
        return entry.checked = selectionModel.containById(entry.name);
    });
}

function updateSelectedList() {
    var list = $.map(selectionModel.getIcecreams(), function(item) {
        console.log('item: ', item);
        return item.name;
    });
    $('#selectedList').text(list.join('>'));
}


// controller
function onClickIcecream(event) {
    var checkbox = $(event.currentTarget).find('input[type="checkbox"]');
    console.log('onClicked', checkbox.attr('name'));
    if (checkbox) {
        var item = icecreamModel.getIcecreamById(checkbox.attr('name'));
        selectionModel.add(item);
    }
}

$(function() {
    var icecreams = $('#icecreams');
    $.each(icecreamModel.getAll(), function(i, entry) {
        icecreams.append(
            $('<li>').append(
                $('<input type="checkbox">')
                    .attr('name', entry.id)
                    .append(
                        $('<span>').text(entry.name)
                    )
            )
            .click(function(event) {
                onClickIcecream(event);
                console.log('clicked', entry.name)
            })
        );
    });
    selectionModel.updateView();
});
