package main

import (
	"encoding/json"
	"errors"
	"log"
	"net/http"
	"strconv"
	"sync"
	"time"
)

type Rezervari struct {
	mu     sync.Mutex
	events map[int64]Event
	nextID int64
}

func NewRezervari() *Rezervari {
	s := &Rezervari{
		events: make(map[int64]Event),
		nextID: 2,
	}
	s.events[0] = Event{ID: 0, Name: "TaiatFrunzeLaCaini", Capacity: 6}
	s.events[1] = Event{ID: 1, Name: "FrecatMenta", Capacity: 7}
	return s
}

func (s *Rezervari) Get(id int64) (Event, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	event, ok := s.events[id]
	if !ok {
		return Event{}, ErrNotFound
	}
	return event, nil
}

var rezervari = NewRezervari()

var (
	ErrNotFound = errors.New("eveniment inexistent")
)

type Event struct {
	ID       int64  `json:"id"`
	Name     string `json:"name"`
	Capacity int    `json:"capacity"`
	Reserved int    `json:"reserved"`
}

func routes() http.Handler {
	mux := http.NewServeMux()
	mux.HandleFunc("GET /health", health)
	///mux.HandleFunc("GET /events", listEvents)
	mux.HandleFunc("GET /events/{id}", getEvent)
	return mux
}

func writeError(w http.ResponseWriter, status int, msg string) {
	writeJSON(w, status, map[string]string{"error": msg})
}

func writeJSON(w http.ResponseWriter, status int, value any) {
	data, err := json.Marshal(value)
	if err != nil {
		status = http.StatusInternalServerError
		data = []byte(`{"error":"eroare internă"}`)
	}
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(status)
	w.Write(data)
}
func health(w http.ResponseWriter, r *http.Request) {
	writeJSON(w, http.StatusOK, map[string]string{"status": "ok"})
}

func getEvent(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.ParseInt(r.PathValue("id"), 10, 64)
	if err != nil || id < 0 {
		writeError(w, http.StatusBadRequest, "id invalid")
		return
	}
	event, err := rezervari.Get(id)
	if errors.Is(err, ErrNotFound) {
		writeError(w, http.StatusNotFound, "eveniment inexistent")
		return
	}
	writeJSON(w, http.StatusOK, event)
}

func main() {
	srv := &http.Server{
		Addr:              "127.0.0.1:8080",
		Handler:           routes(),
		ReadHeaderTimeout: 5 * time.Second,
		WriteTimeout:      10 * time.Second,
	}
	log.Println("server pornit pe http://localhost:8080")
	if err := srv.ListenAndServe(); err != nil && !errors.Is(err, http.ErrServerClosed) {
		log.Fatal(err)
	}
}
