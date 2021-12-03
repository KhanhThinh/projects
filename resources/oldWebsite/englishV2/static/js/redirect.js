var seconds = 6;
// countdown timer. took 6 because page takes approx 1 sec to load

var urlEnglish = "http://englishteaching.herokuapp.com";
// variable for school url

function engRedirect() {
    if (seconds <= 0) {
        window.location = urlEnglish;
    } else {
        seconds--;
        setTimeout("engRedirect()", 1000)
    }
}