nombre.property // ok
(10).property // ok
nombre.property.method() // ok
nombre.property.method(10) // bad any cast

"nombre".property // bad any cast
nombre.method() // bad any cast
