package com.devskiller.library.service;

import com.devskiller.library.exception.BookAlreadyBorrowedException;
import com.devskiller.library.exception.BookBorrowingNotFoundException;
import com.devskiller.library.exception.BookNotAvailableException;
import com.devskiller.library.exception.BookNotFoundException;
import com.devskiller.library.model.Book;
import com.devskiller.library.model.BookBorrowing;
import com.devskiller.library.model.User;
import com.devskiller.library.repository.BooksRepository;
import com.devskiller.library.repository.BorrowingsRepository;

import java.util.List;
import java.util.Optional;

public class BookService {
    private final BooksRepository booksRepository;
    private final BorrowingsRepository borrowingsRepository;

    public BookService(BooksRepository booksRepository, BorrowingsRepository borrowingsRepository) {
        this.booksRepository = booksRepository;
        this.borrowingsRepository = borrowingsRepository;
    }

    public void borrowBook(User user, Book book) {
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        if (countOptional.isEmpty()) {
            throw new BookNotFoundException();
        }

        int count = countOptional.get();
        if (count <= 0) {
            throw new BookNotAvailableException();
        }

        List<BookBorrowing> userBorrowings = borrowingsRepository.getByUser(user);
        for (BookBorrowing borrowing : userBorrowings) {
            if (borrowing.getBook().equals(book)) {
                throw new BookAlreadyBorrowedException();
            }
        }
        userBorrowings.add(new BookBorrowing(book));
        booksRepository.save(book, count - 1);
        borrowingsRepository.save(user, userBorrowings);
    }

    public void returnBook(User user, Book book) {
        List<BookBorrowing> userBorrowings = borrowingsRepository.getByUser(user);
        boolean found = false;
        for (BookBorrowing borrowing : userBorrowings) {
            if (borrowing.getBook().equals(book)) {
                userBorrowings.remove(borrowing);
                found = true;
                break;
            }
        }
        if (!found) {
            throw new BookBorrowingNotFoundException();
        }
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        if(countOptional.isEmpty()) throw new BookNotFoundException();
        booksRepository.save(book, countOptional.get() + 1);
        borrowingsRepository.save(user, userBorrowings);
    }

    public void addBookCopy(Book book) {
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        this.booksRepository.save(book, countOptional.isEmpty()? 1 : countOptional.get() +1 );
    }

    public void removeBookCopy(Book book) {
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        if (countOptional.isEmpty()) {
            throw new BookNotFoundException();
        }

        int count = countOptional.get();
        if (count <= 0) {
            throw new BookNotAvailableException();
        }

        booksRepository.save(book, count - 1);
    }

    public int getAvailableBookCopies(Book book) {
        Optional<Integer> countOptional = booksRepository.getBookCount(book);
        if (countOptional.isEmpty()) {
            throw new BookNotFoundException();
        }

        return countOptional.get();
    }

}
