// Helper method for creating object instances from URI or components.
function createQMLObject( objectURI, aParent, properties ) {
    var component
    properties = typeof properties !== "undefined" ? properties : {}
    component = Qt.createComponent( objectURI )

    if ( component.status === Component.Ready ) {
        return component.createObject( aParent, properties )
    }

    console.log( "Cannot create component for ", objectURI, ", reason", component.errorString() )
    return null
}

// Check if URL is not null or undefined
function isValidURL( aURL ) {
    return aURL !== null && aURL !== undefined && aURL.toString() !== "" && aURL.toString().search( "null" ) === -1
}

// Helper method, returns true is aParent is a recursive parent of aChild
function isParent( aParent, aChild ) {
    if ( !aChild || !aParent ) {
        return false
    }
    if ( aChild.parent && aParent === aChild.parent ) {
        return true
    }

    return isParent( aParent, aChild.parent )
}
