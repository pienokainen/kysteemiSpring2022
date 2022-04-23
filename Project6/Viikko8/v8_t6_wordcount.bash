#!/bin/sh

cat $1 | #käsitellään argumenttina annettua tiedostoa
  tr -cs A-za-z\' '\n' | # korvataan välilyönnit rivinvaihdoilla 
    tr 'A-Z' 'a-z' | # muunnetaan kaikki kirjaimet pieniksi
      sort | # lajitellaan sanat
        uniq -c | #poistaa duplikaatit
          sort -nr | #lajitellaan päinvastaisessa järjestyksessä, jotta nähdään yleisimmät sanat ensimmäisenä
            head -n 10 # näytetään 10 yleisintä sanaa
