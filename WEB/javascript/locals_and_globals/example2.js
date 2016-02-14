



// variables defined outside a function are accessible anywhere once they have been declared,
// they are called global variables, and their scope are global.
// just like other languages I'm used too.


var myNumber = 7; // global variable


var timesTwo = function(number){
	var myNumber = number * 2;// this is a local and will not change the global var value.
	console.log("Inside the function myNumber have changed to: " + myNumber);
	
}

timesTwo(myNumber);
console.log(myNumber);





