var KnockoutMixin ={

    updateKnockout:function(){
        this.__koTrigger(!this.__koTrigger());
    },

    componentDidMount:function(){
        this.__koTrigger = ko.observable(true);
        this.__koModel = ko.computed(function(){
            this.__koTrigger(); // subscribe to changes of this...
            return {
                props: this.props,
                state:this.state
            }
        })
    }
}