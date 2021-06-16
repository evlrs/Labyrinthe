function openMoadl(i) {
    overlay[i].style.display='block';
}

function closeModal(i) {
    overlay[i].style.display='none';
}


var btnPopup = document.getElementsByClassName('btnPopup');
var overlay = document.getElementsByClassName('overlay');
for(var i = 0; i < btnPopup.length; i++)
{   
    btnPopup[i].addEventListener('click',openMoadl);
    openMoadl(i);
}


var btnClose = document.getElementsByClassName('btnClose');
var overlay = document.getElementsByClassName('overlay');
for(var i = 0; i < btnClose.length; i++)
{
    btnClose[i].addEventListener('click',closeModal);
    closeModal(i);     
}