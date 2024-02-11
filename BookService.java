package com.devskiller.library.service;

import com.devskiller.library.exception.*;
import com.devskiller.library.model.Book;
import com.devskiller.library.model.User;
import com.devskiller.library.repository.BooksRepository;
import com.devskiller.library.repository.BorrowingsRepository;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

public class BookService {
    private final BooksRepository booksRepository;
    private final BorrowingsRepository borrowingsRepository;

    public BookService(BooksRepository booksRepository, BorrowingsRepository borrowingsRepository) {
        this.booksRepository = booksRepository;
        this.borrowingsRepository = borrowingsRepository;
    }

    public void borrowBook(User user, Book book) throws BookNotFoundException, BookNotAvailableException, BookAlreadyBorrowedException {
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        if (countOptional.isEmpty()) {
            throw new BookNotFoundException("Book with id " + book.getId() + " not found");
        }
        
        int count = countOptional.get();
        if (count <= 0) {
            throw new BookNotAvailableException("Book with id " + book.getId() + " is not available");
        }
        
        List<BookBorrowing> userBorrowings = borrowingsRepository.getByUser(user);
        for (BookBorrowing borrowing : userBorrowings) {
            if (borrowing.getBook().equals(book)) {
                throw new BookAlreadyBorrowedException("Book with id " + book.getId() + " is already borrowed by user");
            }
        }
        
        booksRepository.save(book, count - 1);
        borrowingsRepository.save(user, createBookBorrowing(user, book));
    }

    public void returnBook(User user, Book book) throws BookBorrowingNotFoundException {
        List<BookBorrowing> userBorrowings = borrowingsRepository.getByUser(user);
        boolean found = false;
        for (BookBorrowing borrowing : userBorrowings) {
            if (borrowing.getBook().equals(book)) {
                found = true;
                break;
            }
        }
        if (!found) {
            throw new BookBorrowingNotFoundException("Book with id " + book.getId() + " is not borrowed by user");
        }
        
        booksRepository.save(book, booksRepository.getAvailableCopiesCount(book.getId()) + 1);
        borrowingsRepository.save(user, userBorrowings);
    }

    public void addBookCopy(Book book) {
        booksRepository.save(book, booksRepository.getAvailableCopiesCount(book.getId()) + 1);
    }

    public void removeBookCopy(Book book) throws BookNotFoundException, BookNotAvailableException {
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        if (countOptional.isEmpty()) {
            throw new BookNotFoundException("Book with id " + book.getId() + " not found");
        }
        
        int count = countOptional.get();
        if (count <= 0) {
            throw new BookNotAvailableException("Book with id " + book.getId() + " is not available");
        }
        
        booksRepository.save(book, count - 1);
    }

    public int getAvailableBookCopies(Book book) throws BookNotFoundException {
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        if (countOptional.isEmpty()) {
            throw new BookNotFoundException("Book with id " + book.getId() + " not found");
        }
        
        return countOptional.get();
    }
    
    private BookBorrowing createBookBorrowing(User user, Book book) {
        return new BookBorrowing(book);
    }
}
