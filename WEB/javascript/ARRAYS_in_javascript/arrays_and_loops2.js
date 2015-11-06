/* sorry, but I'm off to Dalmasca. */

var text = "ee wlelwel  Rafael wle lwlewll";
var myName = "Rafael";

for(var i = 0; i < text.length; ++i)
{
    var hits = [];
    if(text[i] === myName[0])
    {
        
        for(var j = 0; j < i + myName.length; ++j)
        {
           
            hits.push(text[i]);
        }
        


    }
    
        if(hits.length === 0)
            console.log("Your name wasn't found!");
        else
            console.log(hits);
        
    
}
