# Hooks

Hooks are a way to inject information into the generated code by the compiler.
This is typically useful when you would want to perform actions before or after a test runs.

!!! note 
    This is only available with Selenium targets

## API Reference

### `beforeHook()`

Executes before the entire test suite finishes execution.

### `beforeEachHook()`

Executes before each test finishes execution.

### `afterHook()`

Executes after the entire test suite finishes execution.

### `afterEachHook()`

Executes after each test finishes execution.

### `getToken(): string`

Expose a `Bearer` (JWT) token to be used when talking with the LVLM server. 

### `getServerURL(): string`

Expose the LVLM server URL.

### `afterEachAssertHook(message: string, passed: boolean)`

Executes after each `check` action. This is typically used to retrieve the results of the action and send them elsewhere. 

