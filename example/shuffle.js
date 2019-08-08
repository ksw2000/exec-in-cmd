list=['Aquarius','Pisces','Aries','Taurus','Gemini','Cancer','Leo','Virgo','Libra','Scorpio','Sagittarius','Capricorn']
list.sort(function(){
    return Math.random()>.5 ? -1 : 1;
});
console.log("People who love Atom very much:");
for(let i=0; i<5; i++){
    console.log("TOP"+i,":",list[i]);
}
