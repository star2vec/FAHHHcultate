package main

import (
	"database/sql"
	"errors"
	"log"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"

	_ "github.com/glebarez/go-sqlite"
)

const schema = `
CREATE TABLE IF NOT EXISTS products (
	id    INTEGER PRIMARY KEY AUTOINCREMENT,
	name  TEXT NOT NULL,
	price INTEGER NOT NULL,
	stock INTEGER NOT NULL
);`

type Product struct {
	ID    int64  `json:"id"`
	Name  string `json:"name"`
	Price int    `json:"price"`
	Stock int    `json:"stock"`
}

var ErrNotFound = errors.New("produs inexistent")

type ProductStore struct {
	db *sql.DB
}

func NewProductStore(path string) (*ProductStore, error) {
	db, err := sql.Open("sqlite", path)
	if err != nil {
		return nil, err
	}

	db.SetMaxOpenConns(1)
	if err := db.Ping(); err != nil {
		db.Close()
		return nil, err
	}
	if _, err := db.Exec(schema); err != nil {
		db.Close()
		return nil, err
	}

	s := &ProductStore{db: db}

	var n int
	if err := db.QueryRow("SELECT COUNT(*) FROM products").Scan(&n); err != nil {
		db.Close()
		return nil, err
	}
	if n == 0 {
		s.Create("p1", 1, 2)
		s.Create("p2", 3, 4)
		s.Create("p3", 5, 6)
	}
	return s, nil
}
func (s *ProductStore) Close() error {
	return s.db.Close()
}

func (s *ProductStore) Create(name string, price int, stock int) (Product, error) {
	res, err := s.db.Exec("INSERT INTO products (name, price, stock) VALUES (?, ?, ?)", name, price, stock)
	if err != nil {
		return Product{}, err
	}
	id, err := res.LastInsertId()
	if err != nil {
		return Product{}, err
	}
	return Product{ID: id, Name: name, Price: price, Stock: stock}, nil
}

func (s *ProductStore) Get(id int64) (Product, error) {
	var p Product
	err := s.db.QueryRow("SELECT id, name, price, stock FROM products WHERE id = ?", id).
		Scan(&p.ID, &p.Name, &p.Price, &p.Stock)
	if errors.Is(err, sql.ErrNoRows) {
		return Product{}, ErrNotFound
	}
	if err != nil {
		return Product{}, err
	}
	return p, nil
}

func (s *ProductStore) List() ([]Product, error) {
	rows, err := s.db.Query("SELECT id, name, price, stock FROM products ORDER BY id")
	if err != nil {
		return nil, err
	}
	defer rows.Close()
	products := []Product{}
	for rows.Next() {
		var p Product
		if err := rows.Scan(&p.ID, &p.Name, &p.Price, &p.Stock); err != nil {
			return nil, err
		}
		products = append(products, p)
	}
	if err := rows.Err(); err != nil {
		return nil, err
	}
	return products, nil
}

func (s *ProductStore) Update(id int64, name string, price int, stock int) (Product, error) {
	res, err := s.db.Exec("UPDATE products SET name = ?, price = ?, stock = ? WHERE id = ?", name, price, stock, id)
	if err != nil {
		return Product{}, err
	}
	n, err := res.RowsAffected()
	if err != nil {
		return Product{}, err
	}
	if n == 0 {
		return Product{}, ErrNotFound
	}
	return Product{ID: id, Name: name, Price: price, Stock: stock}, nil
}
func (s *ProductStore) Delete(id int64) error {
	res, err := s.db.Exec("DELETE FROM products WHERE id = ?", id)
	if err != nil {
		return err
	}
	n, err := res.RowsAffected()
	if err != nil {
		return err
	}
	if n == 0 {
		return ErrNotFound
	}
	return nil
}

func internalError(c *gin.Context, err error) {
	log.Printf("eroare internă: %v", err)
	c.JSON(http.StatusInternalServerError, gin.H{"error": "eroare internă"})
}

func listProducts(c *gin.Context) {
	products, err := productStore.List()
	if err != nil {
		internalError(c, err)
		return
	}
	c.JSON(http.StatusOK, products)
}

func parseID(c *gin.Context) (int64, bool) {
	id, err := strconv.ParseInt(c.Param("id"), 10, 64)
	if err != nil || id <= 0 {
		c.JSON(http.StatusBadRequest, gin.H{"error": "id invalid"})
		return 0, false
	}
	return id, true
}

func getProduct(c *gin.Context) {
	id, ok := parseID(c)
	if !ok {
		return
	}
	product, err := productStore.Get(id)
	if errors.Is(err, ErrNotFound) {
		c.JSON(http.StatusNotFound, gin.H{"error": "produs inexistent"})
		return
	}
	if err != nil {
		internalError(c, err)
		return
	}
	c.JSON(http.StatusOK, product)
}

var productStore *ProductStore

func main() {
	var err error
	productStore, err = NewProductStore("products.db")
	if err != nil {
		log.Fatal(err)
	}
	defer productStore.Close()

	r := gin.Default()
	products := r.Group("/products")
	products.GET("", listProducts)

	if err := r.Run("localhost:8080"); err != nil {
		log.Fatal(err)
	}
}
