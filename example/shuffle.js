var list = ['Aquarius','Pisces','Aries','Taurus','Gemini','Cancer','Leo','Virgo','Libra','Scorpio','Sagittarius','Capricorn']

function swap(list, i, j){
    let temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}

for(let i=0; i<list.length; i++){
    swap(list, i, Math.floor(Math.random()*(i+1)));
}

console.log("Who loves Atom?");

for(let i=0; i<5; i++){
    console.log("TOP" , i, ":", list[i]);
}
