package com.itscreening.tests.faker;

import java.util.Random;

public class Faker {

    private static final Random random = new Random();

    /**
     * Replaces each question mark character (?) with any random lower a-z letter.
     *
     * @param letterString the string containing question mark characters to replace
     * @return a string with question mark characters replaced with random lower a-z letters
     */
    public String letterify(String letterString) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < letterString.length(); i++) {
            char c = letterString.charAt(i);
            if (c == '?') {
                result.append((char) ('a' + random.nextInt(26))); // Generating random lower a-z letter
            } else {
                result.append(c);
            }
        }
        return result.toString();
    }

    /**
     * Replaces each hash character (#) with any random 0-9 number.
     *
     * @param numberString the string containing hash characters to replace
     * @return a string with hash characters replaced with random 0-9 numbers
     */
    public String numerify(String numberString) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < numberString.length(); i++) {
            char c = numberString.charAt(i);
            if (c == '#') {
                result.append(random.nextInt(10)); // Generating random 0-9 number
            } else {
                result.append(c);
            }
        }
        return result.toString();
    }

    /**
     * Replaces each question mark character (?) with any random lower a-z letter
     * and each hash character (#) with any random 0-9 number.
     *
     * @param string the string containing both question mark and hash characters to replace
     * @return a string with question mark characters replaced with random lower a-z letters
     * and hash characters replaced with random 0-9 numbers
     */
    public String bothify(String string) {
        return numerify(letterify(string));
    }
}
