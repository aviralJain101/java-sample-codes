package com.devskiller.cryptography;

import java.security.*;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.Base64;

public class RSADecryptionService {

    private static final String PRIVATE_KEY_PATH = "src/main/resources/private_key.pem";
    private static final String PUBLIC_KEY_PATH = "src/main/resources/public_key.pem";
    private static final int MAX_DATA_LENGTH = 245; // For RSA 2048-bit key

    public byte[] decrypt(byte[] data) throws InvalidDataLengthException, InvalidDataToDecryptException {
        if (data == null || data.length == 0 || data.length > MAX_DATA_LENGTH) {
            throw new InvalidDataLengthException();
        }

        try {
            Cipher cipher = Cipher.getInstance("RSA");
            PrivateKey privateKey = getPrivateKey();
            cipher.init(Cipher.DECRYPT_MODE, privateKey);
            return cipher.doFinal(data);
        } catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchPaddingException |
                IllegalBlockSizeException | BadPaddingException e) {
            throw new InvalidDataToDecryptException();
        }
    }

    public String decrypt(String dataAsBase64) throws InvalidDataLengthException, InvalidDataToDecryptException {
        if (dataAsBase64 == null || dataAsBase64.isEmpty()) {
            throw new InvalidDataLengthException();
        }

        try {
            byte[] data = Base64.getDecoder().decode(dataAsBase64);
            return new String(decrypt(data), "UTF-8");
        } catch (IllegalArgumentException | UnsupportedEncodingException e) {
            throw new InvalidDataToDecryptException();
        }
    }

    public byte[] sign(byte[] data) throws InvalidDataToDecryptException {
        if (data == null || data.length == 0) {
            throw new InvalidDataToDecryptException();
        }

        try {
            Signature signature = Signature.getInstance("SHA256withRSA");
            PrivateKey privateKey = getPrivateKey();
            signature.initSign(privateKey);
            signature.update(data);
            return signature.sign();
        } catch (NoSuchAlgorithmException | InvalidKeyException | SignatureException e) {
            throw new InvalidDataToDecryptException();
        }
    }

    private PrivateKey getPrivateKey() throws InvalidDataToDecryptException {
        try {
            byte[] keyBytes = Utils.readFromFile(PRIVATE_KEY_PATH);
            PKCS8EncodedKeySpec spec = new PKCS8EncodedKeySpec(keyBytes);
            KeyFactory kf = KeyFactory.getInstance("RSA");
            return kf.generatePrivate(spec);
        } catch (NoSuchAlgorithmException | InvalidKeySpecException e) {
            throw new InvalidDataToDecryptException();
        }
    }

    private PublicKey getPublicKey() throws InvalidDataToDecryptException {
        try {
            byte[] keyBytes = Utils.readFromFile(PUBLIC_KEY_PATH);
            X509EncodedKeySpec spec = new X509EncodedKeySpec(keyBytes);
            KeyFactory kf = KeyFactory.getInstance("RSA");
            return kf.generatePublic(spec);
        } catch (NoSuchAlgorithmException | InvalidKeySpecException e) {
            throw new InvalidDataToDecryptException();
        }
    }
}
