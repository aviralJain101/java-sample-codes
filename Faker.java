package com.itscreening.tests.faker;

import java.util.Random;

public class Faker {
    private static final Random random = new Random();
    public String letterify(String letterString) {
        StringBuilder letter = new StringBuilder();
        for (int i = 0; i < letterString.length(); i++) {
            char element = letterString.charAt(i);
            if (element == '?') {
                letter.append((char) ('a' + random.nextInt(26))); // Generating random lower a-z letter
            } else {
                letter.append(element);
            }
        }
        return letter.toString();
    }

    public String numerify(String numberString) {
        StringBuilder letter = new StringBuilder();
        for (int i = 0; i < numberString.length(); i++) {
            char element = numberString.charAt(i);
            if (element == '#') {
                letter.append(random.nextInt(10)); // Generating random 0-9 number
            } else {
                letter.append(element);
            }
        }
        return letter.toString();

    }

    public String bothify(String string) {
        return numerify(letterify(string));

    }

}
