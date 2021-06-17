function openMoadl(event) {
    var o = 
    event.target.parentNode.getElementsByClassName("overlay")[0];
    o.style.display='block';
   // o.addEventListener('click',closeModal);
}

function closeModal(event) {
    var o = event.target;
    console.log(o.className);
    while (o.className !== "overlay") {
        console.log(o.tagName);
       o = o.parentNode;

    }
    o.style.display='none';
}


var btnPopup = document.getElementsByClassName('btnPopup');
var overlay = document.getElementsByClassName('overlay');
for(var i = 0; i < btnPopup.length; i++)
{   
    btnPopup[i].addEventListener('click',openMoadl);
    //btnPopup[i].openMoadl();
}


var btnClose = document.getElementsByClassName('btnClose');
var overlay = document.getElementsByClassName('overlay');
for(var i = 0; i < btnClose.length; i++)
{
    btnClose[i].addEventListener('click',closeModal);  
}