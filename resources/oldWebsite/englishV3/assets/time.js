setInterval(currentTime, 1000);

function currentTime() {
    let time = new Date();   // creating object of Date class
    let dayName = time.getDay();
    let month = time.getMonth();
    let year = time.getFullYear();
    let date = time.getDate();
    let hour = time.getHours();
    let min = time.getMinutes();
    let sec = time.getSeconds();

    hour = hour < 10 ? "0" + hour : hour;
    min = min < 10 ? "0" + min : min;
    sec = sec < 10 ? "0" + sec : sec;
    date = date < 10 ? "0" + date : date;

    //value of current time
    let currentTime = hour + ":" + min + ":" + sec;

    // value of present day(Day, Month, Year)
    var months = ["tháng 01", "tháng 02", "tháng 03", "tháng 04", "tháng 05", "tháng 06", "tháng 07", "tháng 08", "tháng 09", "tháng 10", "tháng 11", "tháng 12"];
    var week = ["Chủ nhật", "Thứ hai", "Thứ ba", "Thứ tư", "Thứ năm", "Thứ sáu", "Thứ bảy"];

    var presentDay = week[dayName] + ", ngày " + date + " " + months[month] + " năm " + year;

    const clock = document.getElementById("time");
    const dayIntro = document.getElementById("dayName");

    clock.innerHTML = currentTime;
    dayIntro.innerHTML = presentDay;
}

currentTime();